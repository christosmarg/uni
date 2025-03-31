public class ClientInfo {
    public String FullName;

    public String Phone;

    public String BirthDate;

    public String CreditCard;

    public String Address;

	public ClientInfo(String name, String tel, String BD, String CC, String adr) {
		FullName = name;
		Phone = tel;
		BirthDate = BD;
		CreditCard = CC;
		Address = adr;
	}
	
	public String toString()
	{
		return "Name : " + FullName + "\n"
		+ "Phone : " + Phone + "\n"
		+ "Birth day : " + BirthDate + "\n"
		+ "Credit card : " + CreditCard + "\n"
		+ "Address : " + Address + "\n";
	}
}
