package servlet;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import service.AccountService;
import service.AccountServiceImpl;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet{
	private static final long serialVersionUID = 1l;
	@Override
	protected void doGet(HttpServletRequest req,HttpServletResponse resp) {
		this.doPost(req,resp);
	}
	
	@Override
	protected void doPost(HttpServletRequest req,HttpServletResponse resp) {
		try {
			req.setCharacterEncoding("UTF-8");
			
			String name = req.getParameter("name");
			String sex = req.getParameter("sex");
			String password = req.getParameter("password");
			String age = req.getParameter("age");
			System.out.println("name:"+name+" sex:"+sex+" password:"+password+" age:"+age);
			AccountService as = new AccountServiceImpl();
			as.addAccount(name, sex, password, age);
			
			req.getRequestDispatcher("/success.jsp").forward(req, resp);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
}
