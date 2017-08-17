# RedisSim

## description
this is a broker between Application and Redis. with this, we can connect our application to it and it will connect to redis.
## why is this needed?
when testing our Redis application, we may face the message form Redis timeout. we want to simulat the delay case.
## how to use?
please keep in mind, this is a binary or run a thread with your app.
we will got the following parts:
```
1. App client
2. sim server
3. sim connector
4. fake redis
5. command server
6. command server client
```

when start, it listen on a port for input command and do the work accordingly.

when the command server receive a "add forwarder" message, it will start a new forwarder. when a new connection come, forwarder will add sim connector. connector will connect to fake redis(or real redis).

please see example.
