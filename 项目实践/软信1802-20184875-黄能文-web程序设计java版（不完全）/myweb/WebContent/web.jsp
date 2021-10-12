<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<center> hello world!</center>
<UL>
  <LI>Current time: <%= new java.util.Date() %> <%-- 注释jsp里的函数调用 --%>
  <LI>Your hostname: <%= request.getRemoteHost() %>
  <LI>Your session ID: <%= session.getId() %>
  <LI>The <CODE>testParam</CODE> form parameter:
      <%= request.getParameter("testParam") %> <%-- 传参 以及+ --%>>
      
      <form action="main.jsp" method="GET">
站点名: <input type="text" name="name">
<br />
网址: <input type="text" name="url" />
<input type="submit" value="提交" />
</form>
</UL>
</body>
</html>