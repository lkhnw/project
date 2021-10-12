package controller;

public class Account {
	private String name;
	private String sex;
	private String password;
	private String age;
	public Account() {
		super();
	}
	public String getName() {
		return name;
	}
	public void setName(String Name) {
		name = Name;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String Sex) {
		sex = Sex;
	}
	public  String getPassword() {
		return password;
	}
	public void setPAssword(String Password) {
		password = Password;
	}
	public String getAge() {
		return age;
	}
	public void setAge(String Age) {
		age = Age;
	}
	public String toString() {
		return "Account [Name="+name+",Sex=" +sex+",Password="+password+",Age="+age+"]";
	}
}
