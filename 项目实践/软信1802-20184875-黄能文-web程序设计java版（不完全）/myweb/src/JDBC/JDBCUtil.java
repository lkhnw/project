package JDBC;

import java.sql.*;

public class JDBCUtil {
	 //����MySQL�����ݿ���������
	     public static final String DBDRIVER = "com.mysql.jdbc.Driver";
	      //����MySQL���ݿ�����ӵ�ַ
	      public static final String DBURL = "jdbc:mysql://localhost:3306/test";
	     //MySQL���ݿ�������û���
	     public static final String DBUSER = "root";
	     //MySQL���ݿ����������
	     public static final String DBPASS = "123456";
	     
	     //�������ݿ�
	     public static Connection getCon()throws ClassNotFoundException,SQLException{
	    	 Class.forName(DBDRIVER);
	    	 Connection con = DriverManager.getConnection(DBURL,DBUSER,DBPASS);
	    	 return con;
	     }
	     //�ر����ݿ�
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
