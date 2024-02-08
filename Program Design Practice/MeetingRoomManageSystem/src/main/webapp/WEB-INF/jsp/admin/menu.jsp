<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>

<div class="col-md-2">
    <ul class="nav nav-pills nav-stacked" id="nav">
        <li><a href="${pageContext.request.contextPath}/admin/showRoom">Room Management<span class="glyphicon glyphicon-pencil pull-right"/></a></li>
        <li><a href="${pageContext.request.contextPath}/admin/showReservation">Reservation Approval<span class="glyphicon glyphicon-pencil pull-right" /></a></li>
        <li><a href="${pageContext.request.contextPath}/admin/showRecord">Reservation Record Query<span class="glyphicon glyphicon-pencil pull-right" /></a></li>
        <li><a href="${pageContext.request.contextPath}/admin/userRegister">User Management<sapn class="glyphicon glyphicon-repeat pull-right" /></a></li>
        <%--<li><a href="${pageContext.request.contextPath}/admin/passwordReset">修改密码<sapn class="glyphicon glyphicon-pencil pull-right" /></a></li>--%>
        <li><a href="${pageContext.request.contextPath}/logout">Quit<sapn class="glyphicon glyphicon-log-out pull-right" /></a></li>
        <%--<li class="disabled"><a href="##">Responsive</a></li>--%>
    </ul>
</div>