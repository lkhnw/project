package DAO;

public interface AccountDao {
	//ע��
		void InsertAccount(String name,String sex,String password,String age);
		//����
		boolean AccountLogin(String name,String password);
}
