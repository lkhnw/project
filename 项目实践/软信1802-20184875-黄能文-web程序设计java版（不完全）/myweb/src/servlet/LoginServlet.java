package servlet;

import java.io.UnsupportedEncodingException;

import javax.servlet.annotation.WebServlet;
//import javax.servlet.http.HttpServlet;
import javax.servlet.http.*;

import service.AccountService;
import service.AccountServiceImpl;


@WebServlet("/login")
public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID=1l;
	
	protected void doGet(HttpServletRequest request,HttpServletResponse response) throws UnsupportedEncodingException {
		this.doPost(request, response);
	}
	
	protected void doPost(HttpServletRequest request,HttpServletResponse response) throws UnsupportedEncodingException {
		request.setCharacterEncoding("UTF-8");
		
		String name = request.getParameter("name");
		String password = request.getParameter("password");
		
		System.out.println("name:"+name+ " password:"+password);
		AccountService as = new AccountServiceImpl();
		try {
			boolean flag = as.loginAccount(name, password);
			if(flag == true) {
				request.getRequestDispatcher("/info.jsp").forward(request, response);
			}else {
				request.getRequestDispatcher("/error.jsp").forward(request, response);
			}
		}catch(Exception e) {e.printStackTrace();}
	}
}
