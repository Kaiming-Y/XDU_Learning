# B测

## ARP 泛洪攻击 与 ARP 欺骗

### ARP泛洪攻击

#### 防止ARP泛洪攻击

- 配置ARP Miss消息限速（根据源IP地址）

  ``` shell
  arp-miss speed-limit source-ip maximum 200
  ```

  如果网络中有用户向设备发送大量目标IP地址不能解析的IP报文（即路由表中存在该IP报文的目的IP对应的路由表项，但设备上没有该路由表项中下一跳对应的ARP表项），将导致设备触发大量的ARP Miss消息。

  当设备检测到某一源IP地址的IP报文在1秒内触发的ARP Miss消息数量超过了限速值，就认为此源IP地址存在攻击。

  如果同一个源IP地址在1秒内触发的ARP Miss消息个数超过ARP Miss消息限速值，设备会丢弃超过限速值的ARP Miss报文，并默认使用block方式在5分钟内持续丢弃该源IP地址的后续所有ARP Miss报文。

- ARP表项的老化时间

  ``` shell
  int g0/0/0
  arp-fake expire-time 3
  ```

  当老化时间超时后，设备会清除临时ARP表项。此时如果设备转发IP报文匹配不到对应的ARP表项，则会重新触发ARP Miss消息并生成临时ARP表项，如此循环重复。

### ARP 欺骗

#### 防止ARP欺骗

- 静态ARP映射

  ``` shell
  arp static 192.168.5.17 5489-9814-05DE
  ```

- 配置ARP表项严格学习

  只有本设备主动发送的ARP请求报文的应答报文才能触发本设备学习ARP，其他设备主动向本设备发送的ARP报文不能触发本设备学习ARP

  ``` shell
  arp learning strict
  ```

  

