package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import JDBC.JDBCUtil;
public class AccountDaoImpl implements AccountDao {

	String sql = null;
	PreparedStatement ps = null;
	Connection conn = null;
	ResultSet rs =null;
	
	
	@Override
	public void InsertAccount(String name, String sex, String password, String age) {
		// TODO Auto-generated method stub
		try {
			//连接
			conn = JDBCUtil.getCon();
			//拼写SQL
			sql ="INSERT INTO ACCOUNT(name,sex,password,age) VALUE(?,?,?,?)";
			//预编译
			ps = conn.prepareStatement(sql);
			//set？值
			ps.setString(1,name);
			ps.setString(2,sex);
			ps.setString(3, password);
			ps.setString(4, age);
			ps.executeUpdate();
			//关连接
			JDBCUtil.close(conn,ps,rs);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public boolean AccountLogin(String name, String password) {
		// TODO Auto-generated method stub
		boolean flag = false;
		try {
			conn = JDBCUtil.getCon();
			String sql = "select * from Account where name = ? AND password = ? ";
			ps = conn.prepareStatement(sql);
			ps.setString(1, name);
			ps.setString(2,password);
			System.out.println("name : "+name+"password :"+password);
			rs = ps.executeQuery();
			
			if(rs.next()) {
				flag = true;
				return flag;
			}else {
				return flag;
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		return false;
	  }
}
