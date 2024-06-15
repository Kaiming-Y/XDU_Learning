package com.em.dao;

import com.em.domain.User;

/**
 * Created by Admiral on 2018/1/19.
 */
public interface UserMapper {
    public User findUserById(String id);

    public void addNewUser(User user);
}
