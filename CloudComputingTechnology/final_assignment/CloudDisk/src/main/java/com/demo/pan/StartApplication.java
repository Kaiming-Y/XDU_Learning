package com.demo.pan;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class StartApplication {

    public static void main(String[] args) {
        org.springframework.context.ApplicationContext ac = SpringApplication.run(StartApplication.class, args);
        String port = ac.getEnvironment().getProperty("server.port");
        String url = "http://localhost:" + (port == null ? 8080 : port) + "";
        System.out.println("启动后访问主页：" + url);
        try {
            System.setProperty("java.awt.headless", "false");
            java.awt.Desktop.getDesktop().browse(new java.net.URI(url));//自动打开浏览器
        } catch (Exception e) {
            System.out.println("自动打开浏览器失败");
        }
    }

}
