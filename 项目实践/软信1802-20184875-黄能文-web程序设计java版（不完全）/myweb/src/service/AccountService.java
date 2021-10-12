package service;

public interface AccountService {
	//×¢²á
	void addAccount(String name,String sex,String password,String age);
	//µÇÈë
	boolean loginAccount(String name,String password);
}
