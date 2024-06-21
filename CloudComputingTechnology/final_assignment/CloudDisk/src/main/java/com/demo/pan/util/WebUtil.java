package com.demo.pan.util;

import com.demo.pan.dao.model.User;

import javax.servlet.http.HttpServletRequest;

/**
 *
 */
public class WebUtil {

    public static String getUserNameByRequest(HttpServletRequest request) {
        User user = (User) request.getSession().getAttribute("user");
        String userName = user.getUserName();
        if (userName == null) {
            userName = "null";
        }
        return userName;
    }
}
