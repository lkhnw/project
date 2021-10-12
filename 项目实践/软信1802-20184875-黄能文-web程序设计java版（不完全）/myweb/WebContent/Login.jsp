<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<form action="/myweb/login" method="GET">
账号: <input type="text" name="account" required>
<br />
密码: <input type="password" name="password" required>
<br/>
<input type="submit" value="登入" />
<a href = "register.jsp" target = "_blank">注册</a>
</form>
</body>
</html>