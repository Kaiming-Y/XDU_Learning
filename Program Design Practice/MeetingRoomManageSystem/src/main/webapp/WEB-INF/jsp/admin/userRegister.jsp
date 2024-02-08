<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>
<!DOCTYPE html>
<html>
<head>
	<title></title>

	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<!-- 引入bootstrap -->
	<link rel="stylesheet" type="text/css" href="${pageContext.request.contextPath}/css/bootstrap.min.css">
	<!-- 引入JQuery  bootstrap.js-->
	<script src="${pageContext.request.contextPath}/js/jquery-3.2.1.min.js"></script>
	<script src="${pageContext.request.contextPath}/js/bootstrap.min.js"></script>
</head>
<body>
<!-- 顶栏 -->
<jsp:include page="top.jsp"></jsp:include>
<!-- 中间主体 -->
<div class="container" id="content">
	<div class="row">
		<jsp:include page="menu.jsp"></jsp:include>
		<div class="col-md-10">
			<div class="panel panel-default">
				<div class="panel-heading">
					<div class="row">
						<h1 style="text-align: center;">User Management</h1>
					</div>
				</div>
				<div class="panel-body">
					<form class="form-horizontal" name="newUser" role="form" action="${pageContext.request.contextPath}/admin/userRegister" id="editfrom" method="post" onsubmit="check()">
						<div class="form-group">
							<label for="inputEmail3" class="col-sm-2 control-label">User(non-admin)</label>
							<div class="col-sm-10">
								<input type="text" class="form-control" name="id" id="inputEmail3" placeholder="Please enter the user name">
							</div>
						</div>
						<div class="form-group">
							<label for="inputPassword3" class="col-sm-2 control-label">Password</label>
							<div class="col-sm-10">
								<input type="password" class="form-control" id="inputPassword3" placeholder="Please enter the password" name="password">
							</div>
						</div>
						<div class="form-group">
							<label for="inputPassword3" class="col-sm-2 control-label">Confirm</label>
							<div class="col-sm-10">
								<input type="password" class="form-control" name="password2" id="inputPassword3" placeholder="Please confirm the password">
							</div>
						</div>
						<div class="form-group" style="text-align: center">
							<button class="btn btn-default" type="submit">Submit</button>
							<button class="btn btn-default">Reset</button>
						</div>
					</form>
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
<script>
	$("#nav li:nth-child(4)").addClass("active")

	function check() {
		if(newUser.id.value==""||newUser.id.value==null)
		{alert("Please enter the user name");return false;}
		if(newUser.password.value==""||newUser.password.value==null)
		{alert("Please enter the password");return false;}
		if(newUser.password2.value==""||newUser.password2.value==null)
		{alert("Please confirm the password");return false;}
		if(newUser.password.value != newUser.password2.value)
		{alert("Inconsistent!,Please re-enter!");return false;}

	}
</script>
</html>