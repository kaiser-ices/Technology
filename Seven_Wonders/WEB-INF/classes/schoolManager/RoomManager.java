package schoolManager;

import java.util.*;
import java.sql.*;

public class RoomManager{

    private Statement st = null;
    private ResultSet rs = null;

    public RoomManager(DatabaseConnector dc){
	st = dc.getStatement();
    }

    public ArrayList<Room> getAllRooms() throws Exception{

	ArrayList<Room> list = new ArrayList<Room>();
	ResultSet rs = null;

	String sql = "select * from schoolmap_tbl";
	rs = st.executeQuery(sql);

	while(rs.next()){
	    int id = Integer.parseInt(rs.getString("id"));
	    String build = rs.getString("build");
	    int floor = Integer.parseInt(rs.getString("floor"));
	    int count = Integer.parseInt(rs.getString("count"));

	    Room room = new Room(id,build,floor,count);
	    list.add(room);
	}

	return list;

    } 


    public Room getRoomById(String id) throws Exception{
	return getRoomById(Integer.parseInt(id));
    }

    public Room getRoomById(int id) throws Exception{
	
	Room room = null;
	ResultSet rs = null;

	String sql = "select * from schoolmap_tbl where id=" + id;
	rs = st.executeQuery(sql);

	if(!rs.next()){
	    return null;
	}

	room = new Room(id, rs.getString("build"), Integer.parseInt(rs.getString("floor")), Integer.parseInt(rs.getString("count")));


	return room;
    }
}




