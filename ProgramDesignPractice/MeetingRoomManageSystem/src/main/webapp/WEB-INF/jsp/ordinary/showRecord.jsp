<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt"  prefix="fmt" %>

<!DOCTYPE html>
<html>
<head>
	<title>Reservation record query</title>

	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<!-- 引入bootstrap -->
	<link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/css/bootstrap.min.css">
	<!-- 引入JQuery  bootstrap.js-->
	<script src="${pageContext.request.contextPath}/js/jquery-3.2.1.min.js"></script>
	<script src="${pageContext.request.contextPath}/js/bootstrap.min.js"></script>

	<%--<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">--%>

</head>
<body>
	<!-- 顶栏 -->

	<!-- 中间主体 --><jsp:include page="top.jsp"></jsp:include>
	<div class="container" id="content">
		<div class="row">
			<jsp:include page="menu.jsp"></jsp:include>
			<div class="col-md-10">
				<div class="panel panel-default">
				    <div class="panel-heading">
						<div class="row">
					    	<h1 class="col-md-5">Reservation record query</h1>
							<form class="bs-example bs-example-form col-md-5" role="form" style="margin: 20px 0 10px 0;" action="${pageContext.request.contextPath}/ordinary/queryByUser" id="form1" method="post">
								<div class="input-group">
									<input type="text" class="form-control" placeholder="Please enter borrower name" name="findByName">
									<span class="input-group-addon btn" onclick="document.getElementById('form1').submit" id="sub">Search</span>
								</div>
							</form>
						</div>
				    </div>
				    <table class="table table-bordered">
					        <thead>
					            <tr>
									<th>Reservation number</th>
									<th>Meeting room</th>
									<th>Borrower</th>
									<th>Borrow time</th>
									<th>Begin time</th>
									<th>End time</th>
									<th>Status</th>
					            </tr>
					        </thead>
					        <tbody>
							<c:forEach  items="${recordList}" var="item">
								<tr>
									<td>${item.id}</td>
									<td>${item.name}</td>
									<td>${item.user}</td>
									<td><fmt:formatDate value="${item.date}" dateStyle="medium" pattern="yyyy-MM-dd"/></td>
									<!--pattern="HH:mm:ss"为24小时计时法，pattern="hh:mm:ss"为12小时计时法-->
									<td><fmt:formatDate value="${item.beginTime}" dateStyle="medium" pattern="HH:mm:ss"/></td>
									<td><fmt:formatDate value="${item.endTime}" dateStyle="medium" pattern="HH:mm:ss"/></td>
									<td>${item.mark}</td>
								</tr>
							</c:forEach>
					        </tbody>
				    </table>
				    <div class="panel-footer">
						<c:if test="${pagingVo != null}">
							<nav style="text-align: center">
								<ul class="pagination">
									<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.upPageNo}">&laquo;Last page</a></li>
									<li class="active"><a href="">${pagingVo.curentPageNo}</a></li>
									<c:if test="${pagingVo.curentPageNo+1 <= pagingVo.totalCount}">
										<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.curentPageNo+1}">${pagingVo.curentPageNo+1}</a></li>
									</c:if>
									<c:if test="${pagingVo.curentPageNo+2 <= pagingVo.totalCount}">
										<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.curentPageNo+2}">${pagingVo.curentPageNo+2}</a></li>
									</c:if>
									<c:if test="${pagingVo.curentPageNo+3 <= pagingVo.totalCount}">
										<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.curentPageNo+3}">${pagingVo.curentPageNo+3}</a></li>
									</c:if>
									<c:if test="${pagingVo.curentPageNo+4 <= pagingVo.totalCount}">
										<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.curentPageNo+4}">${pagingVo.curentPageNo+4}</a></li>
									</c:if>
									<li><a href="${pageContext.request.contextPath}/ordinary/showRecord?page=${pagingVo.totalCount}">Final page&raquo;</a></li>
								</ul>
							</nav>
						</c:if>
				    </div>
				</div>

			</div>
		</div>
	</div>
	<div class="container" id="footer">
		<div class="row">
			<div class="col-md-12"></div>
		</div>
	</div>
</body>
	<script type="text/javascript">
		$("#nav li:nth-child(2)").addClass("active")

        <c:if test="${pagingVO != null}">
			if (${pagingVO.curentPageNo} == ${pagingVO.totalCount}) {
				$(".pagination li:last-child").addClass("disabled")
			};

			if (${pagingVO.curentPageNo} == ${1}) {
				$(".pagination li:nth-child(1)").addClass("disabled")
			};
        </c:if>

        function confirmd() {
            var msg = "Are you sure you want to delete it? ";
            if (confirm(msg)==true){
                return true;
            }else{
                return false;
            }
        }

        $("#sub").click(function () {
            $("#form1").submit();
        });
	</script>
</html>