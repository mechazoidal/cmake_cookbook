// Taken from https://lists.zeromq.org/pipermail/zeromq-dev/2018-January/032232.html
// This ensures that sockets time out much faster than system defaults.
#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

#define ZMQ_TCP_KEEPALIVE 1
#define ZMQ_TCP_KEEPALIVE_IDLE 30
#define ZMQ_TCP_KEEPALIVE_INTVL 5
#define ZMQ_TCP_KEEPALIVE_CNT 6

#endif  //  __CONFIG_H_INCLUDED__
