import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Room {
	public String type;
	public String desc;
	public int price;
	public int avail;
	private HashMap<String, Integer> guests = new HashMap<String, Integer>();
	private ArrayList<String> listsubs = new ArrayList<String>();

	public Room(String type, String desc, int price, int avail) {
		this.type = type;
		this.desc = desc;
		this.price = price;
		this.avail = avail;
	}

	public String addGuest(String name, int num) {
		if (num <= 0)
			return "fail: cannot book <= 0 rooms";
		else if (avail - num >= 0) {
			guests.put(name, guests.getOrDefault(name, 0) + num);
			avail -= num;
			return "success: " + num * price + "€";
		} else if (avail > 0)
			return "fail: can only book " + avail + " rooms";
		else
			return "fail: no rooms available";
	}

	public String removeReserv(String name, int num) {
		String str = "";
		int n;

		if (!guests.containsKey(name))
			return "guest '" + name + "' doesn't exist";

		/* make sure he doesn't cancel more than he has booked */
		if ((n = guests.get(name)) >= num) {
			guests.put(name, n - num);
			avail += num;
			n -= num;
			/* remove guest if he has 0 reservations */
			if (n == 0) {
				guests.remove(name);
				str += "success";
			} else
				str += "success: " + n + " reservations left";
			str += notifySubs(name);
			return str;
		} else
			return "fail: cannot remove more (" + num +
			    ") than booked (" + n + ")";
	}

	public String listGuests() {
		String str = "";

		for (Map.Entry<String, Integer> g : guests.entrySet())
			str += "\t" + g.getKey() + " (" + g.getValue() + ")\n";
		return str;
	}

	public int totalGuests() {
		return guests.size();
	}

	public void addSub(String name) {
		listsubs.add(name);
	}

	public String notifySubs(String name) {
		if (listsubs.contains(name))
			return "\nnew " + avail + " rooms available!";
		else
			return "";
	}

	public String toString() {
		return avail + " " + type + " (" + desc +
		    ") rooms available - " + price + "€ per night";
	}
}
