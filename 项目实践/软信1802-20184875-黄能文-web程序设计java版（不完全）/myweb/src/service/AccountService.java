package service;

public interface AccountService {
	//ע��
	void addAccount(String name,String sex,String password,String age);
	//����
	boolean loginAccount(String name,String password);
}
