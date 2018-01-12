## 概述
视频直播服务器使用nodejs语言编程，通过http服务接受推流端数据，然后通过websocket连接广播到客户端。

## 启动方式

### Linux
```bash
node websocket-relay.js 10001 10002 &
```

### Window Server
[nodejs 下载地址](https://nodejs.org/en/)

安装成功后，在终端中执行
```bash
node websocket-relay.js 10001 10002
```

[参考文档](https://www.cnblogs.com/cndotabestdota/p/5694629.html)