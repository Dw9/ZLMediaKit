﻿/*
 * Copyright (c) 2016-present The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/ZLMediaKit/ZLMediaKit).
 *
 * Use of this source code is governed by MIT-like license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MK_TCP_H
#define MK_TCP_H

#include "mk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////Buffer::Ptr/////////////////////////////////////////////

typedef struct mk_buffer_t *mk_buffer;
typedef void(API_CALL *on_mk_buffer_free)(void *user_data, void *data);

/**
 * 创建buffer对象
 * @param data 数据指针
 * @param len 数据长度
 * @param cb 数据指针free回调函数，该参数置空时，内部会拷贝数据
 * @param user_data 数据指针free回调函数on_mk_buffer_free第一个参数
 * @return buffer对象
 * Create a buffer object
 * @param data Data pointer
 * @param len Data length
 * @param cb Data pointer free callback function. This parameter is set to null, the data will be copied internally
 * @param user_data The first parameter of the data pointer free callback function on_mk_buffer_free
 * @return buffer object
 
 * [AUTO-TRANSLATED:933f9ad8]
 */
API_EXPORT mk_buffer API_CALL mk_buffer_from_char(const char *data, size_t len, on_mk_buffer_free cb, void *user_data);
API_EXPORT mk_buffer API_CALL mk_buffer_from_char2(const char *data, size_t len, on_mk_buffer_free cb, void *user_data, on_user_data_free user_data_free);
API_EXPORT mk_buffer API_CALL mk_buffer_ref(mk_buffer buffer);
API_EXPORT void API_CALL mk_buffer_unref(mk_buffer buffer);
API_EXPORT const char* API_CALL mk_buffer_get_data(mk_buffer buffer);
API_EXPORT size_t API_CALL mk_buffer_get_size(mk_buffer buffer);

///////////////////////////////////////////SockInfo/////////////////////////////////////////////
// SockInfo对象的C映射  [AUTO-TRANSLATED:6bc64f0f]
// C mapping of SockInfo object
typedef struct mk_sock_info_t *mk_sock_info;

//SockInfo::get_peer_ip()
API_EXPORT const char* API_CALL mk_sock_info_peer_ip(const mk_sock_info ctx, char *buf);
//SockInfo::get_local_ip()
API_EXPORT const char* API_CALL mk_sock_info_local_ip(const mk_sock_info ctx, char *buf);
//SockInfo::get_peer_port()
API_EXPORT uint16_t API_CALL mk_sock_info_peer_port(const mk_sock_info ctx);
//SockInfo::get_local_port()
API_EXPORT uint16_t API_CALL mk_sock_info_local_port(const mk_sock_info ctx);

#ifndef SOCK_INFO_API_RENAME
#define SOCK_INFO_API_RENAME
// mk_tcp_session对象转换成mk_sock_info对象后再获取网络相关信息  [AUTO-TRANSLATED:bd727f26]
// Get network information after converting mk_tcp_session object to mk_sock_info object
#define mk_tcp_session_peer_ip(x,buf) mk_sock_info_peer_ip(mk_tcp_session_get_sock_info(x),buf)
#define mk_tcp_session_local_ip(x,buf) mk_sock_info_local_ip(mk_tcp_session_get_sock_info(x),buf)
#define mk_tcp_session_peer_port(x) mk_sock_info_peer_port(mk_tcp_session_get_sock_info(x))
#define mk_tcp_session_local_port(x) mk_sock_info_local_port(mk_tcp_session_get_sock_info(x))

// mk_tcp_client对象转换成mk_sock_info对象后再获取网络相关信息  [AUTO-TRANSLATED:e642eaac]
// Get network information after converting mk_tcp_client object to mk_sock_info object
#define mk_tcp_client_peer_ip(x,buf) mk_sock_info_peer_ip(mk_tcp_client_get_sock_info(x),buf)
#define mk_tcp_client_local_ip(x,buf) mk_sock_info_local_ip(mk_tcp_client_get_sock_info(x),buf)
#define mk_tcp_client_peer_port(x) mk_sock_info_peer_port(mk_tcp_client_get_sock_info(x))
#define mk_tcp_client_local_port(x) mk_sock_info_local_port(mk_tcp_client_get_sock_info(x))
#endif
///////////////////////////////////////////TcpSession/////////////////////////////////////////////
// TcpSession对象的C映射  [AUTO-TRANSLATED:df12e714]
// C mapping of TcpSession object
typedef struct mk_tcp_session_t *mk_tcp_session;
typedef struct mk_tcp_session_ref_t *mk_tcp_session_ref;

// 获取基类指针以便获取其网络相关信息  [AUTO-TRANSLATED:725bdbd0]
// Get the base class pointer to get its network information
API_EXPORT mk_sock_info API_CALL mk_tcp_session_get_sock_info(const mk_tcp_session ctx);

//TcpSession::safeShutdown()
API_EXPORT void API_CALL mk_tcp_session_shutdown(const mk_tcp_session ctx,int err,const char *err_msg);
//TcpSession::send()
API_EXPORT void API_CALL mk_tcp_session_send(const mk_tcp_session ctx, const char *data, size_t len);
API_EXPORT void API_CALL mk_tcp_session_send_buffer(const mk_tcp_session ctx, mk_buffer buffer);

// 切换到该对象所在线程后再TcpSession::send()  [AUTO-TRANSLATED:8a8f72ac]
// Switch to the thread where the object is located, then TcpSession::send()
API_EXPORT void API_CALL mk_tcp_session_send_safe(const mk_tcp_session ctx, const char *data, size_t len);
API_EXPORT void API_CALL mk_tcp_session_send_buffer_safe(const mk_tcp_session ctx, mk_buffer buffer);

// 创建mk_tcp_session的强引用  [AUTO-TRANSLATED:9dff998d]
// Create a strong reference to mk_tcp_session
API_EXPORT mk_tcp_session_ref API_CALL mk_tcp_session_ref_from(const mk_tcp_session ctx);
// 删除mk_tcp_session的强引用  [AUTO-TRANSLATED:583848b0]
// Delete the strong reference to mk_tcp_session
API_EXPORT void mk_tcp_session_ref_release(const mk_tcp_session_ref ref);
// 根据强引用获取mk_tcp_session  [AUTO-TRANSLATED:4bf1f7a0]
// Get mk_tcp_session according to the strong reference
API_EXPORT mk_tcp_session mk_tcp_session_from_ref(const mk_tcp_session_ref ref);

// /////////////////////////////////////////自定义tcp服务/////////////////////////////////////////////  [AUTO-TRANSLATED:25f12aa6]
// /////////////////////////////////////////Custom tcp service/////////////////////////////////////////////

typedef struct {
    /**
     * 收到mk_tcp_session创建对象
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * Receive mk_tcp_session create object
     * @param server_port Server port number
     * @param session Session processing object
     
     * [AUTO-TRANSLATED:58183e28]
     */
    void (API_CALL *on_mk_tcp_session_create)(uint16_t server_port,mk_tcp_session session);

    /**
     * 收到客户端发过来的数据
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param buffer 数据
     * Receive data sent by the client
     * @param server_port Server port number
     * @param session Session processing object
     * @param buffer Data
     
     * [AUTO-TRANSLATED:ff2132fa]
     */
    void (API_CALL *on_mk_tcp_session_data)(uint16_t server_port,mk_tcp_session session, mk_buffer buffer);

    /**
     * 每隔2秒的定时器，用于管理超时等任务
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * Timer every 2 seconds, used to manage timeout tasks
     * @param server_port Server port number
     * @param session Session processing object
     
     * [AUTO-TRANSLATED:5d36ea59]
     */
    void (API_CALL *on_mk_tcp_session_manager)(uint16_t server_port,mk_tcp_session session);

    /**
     * 一般由于客户端断开tcp触发
     * @param server_port 服务器端口号
     * @param session 会话处理对象
     * @param code 错误代码
     * @param msg 错误提示
     * Generally triggered by client disconnecting tcp
     * @param server_port Server port number
     * @param session Session processing object
     * @param code Error code
     * @param msg Error message
     
     * [AUTO-TRANSLATED:a2e6ce8b]
     */
    void (API_CALL *on_mk_tcp_session_disconnect)(uint16_t server_port,mk_tcp_session session,int code,const char *msg);
} mk_tcp_session_events;


typedef enum {
    // 普通的tcp  [AUTO-TRANSLATED:b4035d33]
    // Ordinary tcp
    mk_type_tcp = 0,
    // ssl类型的tcp  [AUTO-TRANSLATED:88792584]
    // ssl type tcp
    mk_type_ssl = 1,
    // 基于websocket的连接  [AUTO-TRANSLATED:01f3223d]
    // Websocket based connection
    mk_type_ws = 2,
    // 基于ssl websocket的连接  [AUTO-TRANSLATED:86411da9]
    // Ssl websocket based connection
    mk_type_wss = 3
}mk_tcp_type;

/**
 * tcp会话对象附着用户数据
 * 该函数只对mk_tcp_server_server_start启动的服务类型有效
 * @param session 会话对象
 * @param user_data 用户数据指针
 * Attach user data to the tcp session object
 * This function is only valid for services started by mk_tcp_server_server_start
 * @param session Session object
 * @param user_data User data pointer
 
 * [AUTO-TRANSLATED:272bd460]
 */
API_EXPORT void API_CALL mk_tcp_session_set_user_data(mk_tcp_session session, void *user_data);
API_EXPORT void API_CALL mk_tcp_session_set_user_data2(mk_tcp_session session, void *user_data, on_user_data_free user_data_free);

/**
 * 获取tcp会话对象上附着的用户数据
 * 该函数只对mk_tcp_server_server_start启动的服务类型有效
 * @param session tcp会话对象
 * @return 用户数据指针
 * Get the user data attached to the tcp session object
 * This function is only valid for services started by mk_tcp_server_server_start
 * @param session Tcp session object
 * @return User data pointer
 
 * [AUTO-TRANSLATED:8047a5a4]
 */
API_EXPORT void* API_CALL mk_tcp_session_get_user_data(mk_tcp_session session);

/**
 * 开启tcp服务器
 * @param port 监听端口号，0则为随机
 * @param type 服务器类型
 * Start tcp server
 * @param port Listening port number, 0 is random
 * @param type Server type
 
 * [AUTO-TRANSLATED:ad27f0ed]
 */
API_EXPORT uint16_t API_CALL mk_tcp_server_start(uint16_t port, mk_tcp_type type);

/**
 * 监听tcp服务器事件
 * Listen for tcp server events
 
 * [AUTO-TRANSLATED:7ca82a56]
 */
API_EXPORT void API_CALL mk_tcp_server_events_listen(const mk_tcp_session_events *events);


// /////////////////////////////////////////自定义tcp客户端/////////////////////////////////////////////  [AUTO-TRANSLATED:e5ae198e]
// /////////////////////////////////////////Custom tcp client/////////////////////////////////////////////

typedef struct mk_tcp_client_t *mk_tcp_client;
// 获取基类指针以便获取其网络相关信息  [AUTO-TRANSLATED:725bdbd0]
// Get the base class pointer to get its network information
API_EXPORT mk_sock_info API_CALL mk_tcp_client_get_sock_info(const mk_tcp_client ctx);

typedef struct {
    /**
     * tcp客户端连接服务器成功或失败回调
     * @param client tcp客户端
     * @param code 0为连接成功，否则为失败原因
     * @param msg 连接失败错误提示
     * Tcp client connects to server successfully or fails callback
     * @param client Tcp client
     * @param code 0 for successful connection, otherwise for failure reason
     * @param msg Connection failure error message
     
     * [AUTO-TRANSLATED:2b38e72a]
     */
    void (API_CALL *on_mk_tcp_client_connect)(mk_tcp_client client,int code,const char *msg);

    /**
     * tcp客户端与tcp服务器之间断开回调
     * 一般是eof事件导致
     * @param client tcp客户端
     * @param code 错误代码
     * @param msg 错误提示
     * Tcp client disconnects from tcp server callback
     * Generally caused by eof event
     * @param client Tcp client
     * @param code Error code
     * @param msg Error message
     
     * [AUTO-TRANSLATED:5658c1c5]
     */
    void (API_CALL *on_mk_tcp_client_disconnect)(mk_tcp_client client,int code,const char *msg);

    /**
     * 收到tcp服务器发来的数据
     * @param client tcp客户端
     * @param buffer 数据
     * Receive data sent by the tcp server
     * @param client Tcp client
     * @param buffer Data
     
     * [AUTO-TRANSLATED:4a225334]
     */
    void (API_CALL *on_mk_tcp_client_data)(mk_tcp_client client, mk_buffer buffer);

    /**
     * 每隔2秒的定时器，用于管理超时等任务
     * @param client tcp客户端
     * Timer every 2 seconds, used to manage timeout tasks
     * @param client Tcp client
     
     * [AUTO-TRANSLATED:05f637ef]
     */
    void (API_CALL *on_mk_tcp_client_manager)(mk_tcp_client client);
} mk_tcp_client_events;

/**
 * 创建tcp客户端
 * @param events 回调函数结构体
 * @param user_data 用户数据指针
 * @param type 客户端类型
 * @return 客户端对象
 * Create tcp client
 * @param events Callback function structure
 * @param user_data User data pointer
 * @param type Client type
 * @return Client object
 
 * [AUTO-TRANSLATED:01191226]
 */
API_EXPORT mk_tcp_client API_CALL mk_tcp_client_create(mk_tcp_client_events *events, mk_tcp_type type);

/**
 * 释放tcp客户端
 * @param ctx 客户端对象
 * Release the tcp client
 * @param ctx Client object
 
 * [AUTO-TRANSLATED:b3a75d23]
 */
API_EXPORT void API_CALL mk_tcp_client_release(mk_tcp_client ctx);

/**
 * 发起连接
 * @param ctx 客户端对象
 * @param host 服务器ip或域名
 * @param port 服务器端口号
 * @param time_out_sec 超时时间
 * Initiate connection
 * @param ctx Client object
 * @param host Server ip or domain name
 * @param port Server port number
 * @param time_out_sec Timeout time
 
 * [AUTO-TRANSLATED:dd45e0fa]
 */
API_EXPORT void API_CALL mk_tcp_client_connect(mk_tcp_client ctx, const char *host, uint16_t port, float time_out_sec);

/**
 * 非线程安全的发送数据
 * 开发者如果能确保在本对象网络线程内，可以调用此此函数
 * @param ctx 客户端对象
 * @param data 数据指针
 * @param len 数据长度，等于0时，内部通过strlen获取
 * Non-thread-safe data sending
 * Developers can call this function if they can ensure that it is within the network thread of this object
 * @param ctx Client object
 * @param data Data pointer
 * @param len Data length, 0 means get it by strlen internally
 
 * [AUTO-TRANSLATED:a5e2ac86]
 */
API_EXPORT void API_CALL mk_tcp_client_send(mk_tcp_client ctx, const char *data, int len);
API_EXPORT void API_CALL mk_tcp_client_send_buffer(mk_tcp_client ctx, mk_buffer buffer);

/**
 * 切换到本对象的网络线程后再发送数据
 * @param ctx 客户端对象
 * @param data 数据指针
 * @param len 数据长度，等于0时，内部通过strlen获取
 * Send data after switching to the network thread of this object
 * @param ctx Client object
 * @param data Data pointer
 * @param len Data length, 0 means get it by strlen internally
 
 * [AUTO-TRANSLATED:95dc75f8]
 */
API_EXPORT void API_CALL mk_tcp_client_send_safe(mk_tcp_client ctx, const char *data, int len);
API_EXPORT void API_CALL mk_tcp_client_send_buffer_safe(mk_tcp_client ctx, mk_buffer buffer);

/**
 * 客户端附着用户数据
 * @param ctx 客户端对象
 * @param user_data 用户数据指针
 * Client attaches user data
 * @param ctx Client object
 * @param user_data User data pointer
 
 * [AUTO-TRANSLATED:a9d4840b]
 */
API_EXPORT void API_CALL mk_tcp_client_set_user_data(mk_tcp_client ctx, void *user_data);
API_EXPORT void API_CALL mk_tcp_client_set_user_data2(mk_tcp_client ctx, void *user_data, on_user_data_free user_data_free);

/**
 * 获取客户端对象上附着的用户数据
 * @param ctx 客户端对象
 * @return 用户数据指针
 * Get the user data attached to the client object
 * @param ctx Client object
 * @return User data pointer
 
 
 * [AUTO-TRANSLATED:7f74985b]
 */
API_EXPORT void* API_CALL mk_tcp_client_get_user_data(mk_tcp_client ctx);

#ifdef __cplusplus
}
#endif
#endif //MK_TCP_H
