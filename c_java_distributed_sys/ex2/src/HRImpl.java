public class HRImpl implements HRInterface {
	Room[] rooms = {
		new Room("A", "single", 60, 25),
		new Room("B", "double", 80, 40),
		new Room("C", "twin", 90, 20),
		new Room("D", "triple", 115, 15),
		new Room("E", "quad", 140, 10),
	};

	public HRImpl() {
		super();
	}

	public String list() {
		String str = "";

		for (Room r : rooms)
			str += r.toString() + "\n";
		return str;
	}

	public String book(String type, int num, String name) {
		for (Room r : rooms) {
			if (type.equals(r.type))
				return r.addGuest(name, num);
		}
		return fail();
	}

	public String guests() {
		String str = "";
		int n = 0;

		for (Room r : rooms)
			n += r.totalGuests();
		str += "total guests: " + n + "\n";
		for (Room r : rooms) {
			str += r.toString() + "\n";
			if ((n = r.totalGuests()) != 0)
				str += r.listGuests();
		}
		return str;
	}

	public String cancel(String type, int num, String name) {
		for (Room r : rooms) {
			if (type.equals(r.type))
				return r.removeReserv(name, num);
		}
		return fail();
	}

	public void addListSub(String name, String type) {
		for (Room r : rooms) {
			if (type.equals(r.type)) {
				r.addSub(name);
				break;
			}
		}
	}

	private String fail() {
		return "fail: room doesn't exist. available rooms types:\n" +
		    list();
	}
}
