#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mosquitto.h>


void my_message_callback(void *obj, const struct mosquitto_message *message) {

  if(message->payloadlen){
     printf("%s %s\n", message->topic, message->payload);
  }else{
     printf("%s (null)\n", message->topic);
  }
    fflush(stdout);
}


int main(int argc, char *argv[])
{

  char id[30];
  int i;
  char *host = "127.0.0.1";
  int port = 1883;
  int keepalive = 60;
  bool clean_session = true;
  struct mosquitto *mosq = NULL;
  int mosq_err;
  uint16_t *mid;


  mosq = mosquitto_new(id, NULL);


  if(!mosq){
    fprintf(stderr, "Error: Out of memory.\n");
    return 1;
  }

  mosquitto_log_init(mosq, MOSQ_LOG_DEBUG | MOSQ_LOG_ERR | MOSQ_LOG_WARNING
                        | MOSQ_LOG_NOTICE | MOSQ_LOG_INFO, MOSQ_LOG_STDERR);

  mosquitto_message_callback_set(mosq, my_message_callback);
  printf ("CallBack\n"); 

  char *payload = "hola mundo";
  char *topic = "hola/mundo";


      if(mosquitto_connect(mosq, host, port, keepalive, clean_session)){
                fprintf(stderr, "Unable to connect.\n");
                return 1;
        }

  while (1){
    mosq_err = mosquitto_loop(mosq, -1);
    printf ("Publicando % d\n", mosq_err); 
    sleep (1); 
    printf ("Publicando\n"); 
    mosquitto_publish(mosq, mid, topic, 10, payload, 2, 1);
  }
  mosquitto_destroy(mosq);
  return 0;
}
