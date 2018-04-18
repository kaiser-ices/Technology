package schoolManager;

public class Room{

    private int id = 0;
    private String build = "";
    private int floor = 0;
    private int count = 0;

    public Room(int id, String build, int floor, int count){

	this.id = id;
	this.build = build;
	this.floor = floor;
	this.count = count;

    }

    public int getId(){

	return id;

    }

    public String getBuild(){

	return build;

    }

    public int getFloor(){

	return floor;

    }

    public int getCount(){

	return count;

    }
}







