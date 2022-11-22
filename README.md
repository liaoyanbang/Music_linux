# Music_linux
use QT to servey and control linux board to play music  
基于linux平台的智能音箱 - 软件开发2022.08.20 - 2022.10.20
项目描述：该项目采用C/S架构实现了QT桌面客户端通过访问服务端去控制linux音箱的暂停、播放、切歌、增减音量和文件传输等功能；
1. linux音箱通过监听网络消息以及检测本机按键，多进程实现播放音乐；
2. 服务端采用libevent框架实现了对客户端连接请求和网络消息接收的并发处理；
3. 采用Tcp协议以及Json数据格式进行服务端与客户端、服务端与linux音箱的网络通信和数据解析；
4. 编写驱动程序通过访问设备树生成设备节点，实现获取按键值以及控制led的亮灭；
5. 采用微服务实现从客户端传输本地音乐文件至服务器本地，并更新全部歌曲。
