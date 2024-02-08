DROP DATABASE IF EXISTS meeting ;
CREATE DATABASE meeting CHARACTER SET utf8;
use meeting ;

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for reservation
-- ----------------------------
DROP TABLE IF EXISTS `reservation`;
CREATE TABLE `reservation`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `room_id` int(11) NULL DEFAULT NULL,
  `user` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `mobile` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `date` date NULL DEFAULT NULL,
  `begintime` time NULL DEFAULT NULL,
  `endtime` time NULL DEFAULT NULL,
  `mark` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_reservation_room`(`room_id`) USING BTREE,
  CONSTRAINT `fk_reservation_room` FOREIGN KEY (`room_id`) REFERENCES `room` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 36 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of reservation
-- ----------------------------
INSERT INTO `reservation` VALUES (1, 1, 'ordinary', '13988888888', '2018-01-02', '13:30:00', '15:00:00', 'pass');
INSERT INTO `reservation` VALUES (2, 2, 'ordinary', '13988888888', '2018-01-06', '15:00:00', '16:30:00', 'pass');
INSERT INTO `reservation` VALUES (3, 1, 'ordinary', '13988888888', '2018-01-08', '09:00:00', '11:00:00', 'pass');
INSERT INTO `reservation` VALUES (4, 1, 'ordinary', '13988888888', '2018-01-09', '15:00:00', '16:30:00', 'pass');
INSERT INTO `reservation` VALUES (5, 3, 'ordinary', '13988888888', '2018-01-12', '10:00:00', '12:00:00', 'pass');
INSERT INTO `reservation` VALUES (6, 2, 'ordinary', '13988888888', '2018-01-12', '13:00:00', '15:00:00', 'pass');
INSERT INTO `reservation` VALUES (8, 1, 'ordinary', '13988888888', '2018-01-22', '09:00:00', '10:00:00', 'cancel');
INSERT INTO `reservation` VALUES (9, 1, 'ordinary', '13988888888', '2018-01-22', '10:30:00', '11:30:00', 'pending');
INSERT INTO `reservation` VALUES (10, 2, 'ordinary', '13988888888', '2018-01-22', '15:00:00', '17:00:00', 'pass');
INSERT INTO `reservation` VALUES (11, 3, 'ordinary', '13988888888', '2018-01-22', '10:00:00', '12:00:00', 'pending');
INSERT INTO `reservation` VALUES (12, 3, 'ordinary', '13988888888', '2018-01-23', '09:00:00', '10:00:00', 'pass');
INSERT INTO `reservation` VALUES (13, 1, 'ordinary', '13988888888', '2018-01-24', '09:00:00', '10:00:00', 'cancel');
INSERT INTO `reservation` VALUES (14, 1, 'ordinary', '13988888888', '2018-02-02', '09:00:00', '10:00:00', 'pass');
INSERT INTO `reservation` VALUES (15, 1, '201801', '13988888888', '2018-02-10', '09:00:00', '10:00:00', 'pending');
INSERT INTO `reservation` VALUES (16, 3, '201801', '13988888888', '2018-02-10', '10:00:00', '11:00:00', 'pending');
INSERT INTO `reservation` VALUES (17, 1, '201801', '13988888888', '2018-02-10', '00:30:00', '13:30:00', 'pass');
INSERT INTO `reservation` VALUES (30, 2, 'ordinary', '', '2022-06-06', '09:00:00', '09:00:00', 'pending');
INSERT INTO `reservation` VALUES (31, 1, 'ordinary', '', '2022-06-06', '09:00:00', '09:00:00', 'pending');
INSERT INTO `reservation` VALUES (32, 1, 'ordinary', '', '2022-06-06', '09:00:00', '09:00:00', 'pending');
INSERT INTO `reservation` VALUES (33, 1, 'ordinary', '', '2022-06-06', '09:00:00', '09:00:00', 'pending');
INSERT INTO `reservation` VALUES (34, 1, 'ordinary', '', '2022-06-06', '09:00:00', '18:00:00', 'pending');
INSERT INTO `reservation` VALUES (35, 1, 'ordinary', '', '2022-06-11', '09:00:00', '09:00:00', 'pending');

-- ----------------------------
-- Table structure for role
-- ----------------------------
DROP TABLE IF EXISTS `role`;
CREATE TABLE `role`  (
  `role_id` int(11) NOT NULL,
  `role_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`role_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of role
-- ----------------------------
INSERT INTO `role` VALUES (1, 'admin');
INSERT INTO `role` VALUES (2, 'ordinary');

-- ----------------------------
-- Table structure for room
-- ----------------------------
DROP TABLE IF EXISTS `room`;
CREATE TABLE `room`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `message` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of room
-- ----------------------------
INSERT INTO `room` VALUES (1, 'J305', '大型会议室，可使用多媒体，适合开会、讲座');
INSERT INTO `room` VALUES (2, '第一会议室327', '能够使用多媒体，适合组会，论文答辩');
INSERT INTO `room` VALUES (3, '第三会议室329', '能够使用多媒体，适合开组会，硕/博士毕业论文答辩');
INSERT INTO `room` VALUES (4, 'J123', '大型会议室，可容纳200人，适合举办讲座');
INSERT INTO `room` VALUES (5, 'J226', '小包间会议室，适合小组讨论');
INSERT INTO `room` VALUES (6, 'J211', '小会议室，适合二十人小型会议，含多媒体');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `role` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_user_role`(`role`) USING BTREE,
  CONSTRAINT `fk_user_role` FOREIGN KEY (`role`) REFERENCES `role` (`role_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('201801', '123456', 2);
INSERT INTO `user` VALUES ('admin', '123456', 1);
INSERT INTO `user` VALUES ('ordinary', '123456', 2);

SET FOREIGN_KEY_CHECKS = 1;
