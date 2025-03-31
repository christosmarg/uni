public class FlightInfo {
    public String flightCode;
    public String originCountry;
    public String timePos;
    public String lng;
    public String lat;
    public String velocity;

    public FlightInfo(String flightCode,String originCountry, String timePos, String lng, String lat, String velocity) {
        this.flightCode = flightCode;
        this.originCountry = originCountry;
        this.timePos = timePos;
        this.lng = lng;
        this.lat = lat;
        this.velocity = velocity;
    }
}
