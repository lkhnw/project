package DAO;

import java.awt.List;
import java.awt.print.Book;

public interface BookDao {
public List getAll();
	
	//根据id获取书
	public Book find(String id);

}
