package service;

import DAO.AccountDao;
import DAO.AccountDaoImpl;

public class AccountServiceImpl implements AccountService {
	@Override
	public void addAccount(String name,String sex,String password,String age) {
		AccountDao dao = new AccountDaoImpl();
		
		try {
			dao.InsertAccount(name, sex, password, age);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	@Override 
	public boolean loginAccount(String name,String password) {
		AccountDao dao = new AccountDaoImpl();
		return dao.AccountLogin(name, password);
	}
}
