package JDBC;

import java.sql.*;

public class JDBCUtil {
	 //定义MySQL的数据库驱动程序
	     public static final String DBDRIVER = "com.mysql.jdbc.Driver";
	      //定义MySQL数据库的连接地址
	      public static final String DBURL = "jdbc:mysql://localhost:3306/test";
	     //MySQL数据库的连接用户名
	     public static final String DBUSER = "root";
	     //MySQL数据库的连接密码
	     public static final String DBPASS = "123456";
	     
	     //连接数据库
	     public static Connection getCon()throws ClassNotFoundException,SQLException{
	    	 Class.forName(DBDRIVER);
	    	 Connection con = DriverManager.getConnection(DBURL,DBUSER,DBPASS);
	    	 return con;
	     }
	     //关闭数据库
	     public static void close(Connection con,PreparedStatement ps,ResultSet rs)throws Exception{
	    	 if(rs!=null) {
	    		 rs.close();
	    	 }
	    	 if(ps!=null) {
	    		 ps.close();
	    	 }
	    	 if(con!=null) {
	    		 con.close();
	    	 }
	     }
}
