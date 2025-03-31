import java.util.ArrayList;

public class MetalDetector {
    public int ID;
    public float Threshold;
    public ArrayList<Float> PreviousScans;

    public MetalDetector(int ID, float threshold) {
        this.ID = ID;
        Threshold = threshold;
        PreviousScans = new ArrayList<>();
    }

    public boolean ScanPassenger(ArrayList<Item> Items)
    {
        float total_thresh = 0;
        for (Item I : Items)
        {
            if (I.Material.equals("Metal")
            || I.Material.equals("Steel")
            || I.Material.equals("Iron"))
            {
                total_thresh += I.Mass;
            }
        }
        PreviousScans.add(total_thresh);
        return Threshold > total_thresh;
    }

}
