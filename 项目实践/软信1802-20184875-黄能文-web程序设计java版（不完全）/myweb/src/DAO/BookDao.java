package DAO;

import java.awt.List;
import java.awt.print.Book;

public interface BookDao {
public List getAll();
	
	//����id��ȡ��
	public Book find(String id);

}
