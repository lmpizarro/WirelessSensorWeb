#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <mosquitto.h>


#define RAW_MESSAGE_LEN   64
#define TIME_TAG_LEN      32 
#define PAYLOAD_LEN       128 

void my_message_callback(void *obj, const struct mosquitto_message *message) {

  if(message->payloadlen){
     printf("%s %s\n", message->topic, message->payload);
  }else{
     printf("%s (null)\n", message->topic);
  }
    fflush(stdout);
}

/*
  
*/
void setTimeTag (char *rawMessage){
    struct tm *newtime;
    time_t ltime;

    /* Get the time in seconds */
    time(&ltime);
    /* Convert it to the structure tm */
    newtime = localtime(&ltime);
    //asctime_r(newtime, rawMessage);
    //rawMessage[24] ='-';
    strftime(rawMessage, TIME_TAG_LEN, "%Y/%m/%d %H:%M:%S-", newtime);
/*   printf("%d/%d/%d-%d:%d:%d-%s\n",
                                   newtime->tm_year+1900, 
                                   newtime->tm_mon+1, 
                                   newtime->tm_mday, 
                                   newtime->tm_hour,  
                                   newtime->tm_min, 
                                   newtime->tm_sec);*/
}

int main(int argc, char *argv[])
{
  char id [32];
  char *host = "127.0.0.1";
  int port = 1883;
  int keepalive = 60;
  bool clean_session = true;
  struct mosquitto *mosq = NULL;
  int mosq_err;
  uint16_t *mid;

  uint8_t *sensorMsg  = malloc (RAW_MESSAGE_LEN); 
  uint8_t *payload  = malloc (64);
  uint8_t *timeTag = malloc (TIME_TAG_LEN); 





  sensorMsg[1]='l';
  sensorMsg[20]='\0';

  mosq = mosquitto_new(id, NULL);


  if(!mosq){
    fprintf(stderr, "Error: Out of memory.\n");
    return 1;
  }

  mosquitto_log_init(mosq, MOSQ_LOG_DEBUG | MOSQ_LOG_ERR | MOSQ_LOG_WARNING
                        | MOSQ_LOG_NOTICE | MOSQ_LOG_INFO, MOSQ_LOG_STDERR);

  mosquitto_message_callback_set(mosq, my_message_callback);
  printf ("CallBack\n"); 

  char *topic = "hola/mundo";

//  printf ("%s\n",sensorMsg); 

      if(mosquitto_connect(mosq, host, port, keepalive, clean_session)){
                fprintf(stderr, "Unable to connect.\n");
                return 1;
        }

  while (1){
    mosq_err = mosquitto_loop(mosq, -1);
    printf ("Publicando % d\n", mosq_err); 
    sleep (1); 
    printf ("Publicando\n"); 
    strcpy(sensorMsg, "0123456789abcdef012");
    strcpy(timeTag,   "2012/04/05-10:02:23-");
    setTimeTag(timeTag);
    strcpy(payload, timeTag);
    strcat(payload,sensorMsg); 
    mosquitto_publish(mosq, mid, topic, strlen(payload), payload, 0, 1);
  }
  mosquitto_destroy(mosq);
  return 0;
}
