<%@ page language="java" contentType="text/html; charset=Utf-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>注册</title>
</head>
<body>
<form action="/myweb/register" method = "POST">
账号：<input type = "text" name = "account" > <br/>
性别：<input type = "text" name = "sex"><br/>
密码：<input type = "password" name = "password"><br>
年龄：<input types = "age" name = age>
<input type = "submit" value = "注册">
</form>
</body>
</html>