package DAO;

public interface AccountDao {
	//×¢²á
		void InsertAccount(String name,String sex,String password,String age);
		//µÇÈë
		boolean AccountLogin(String name,String password);
}
