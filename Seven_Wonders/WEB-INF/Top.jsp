<%@ page contentType="text/html;charset=UTF-8"%>
<jsp:useBean id="message" class="java.lang.String" scope="request"/>
<jsp:useBean id="userName" class="java.lang.String" scope="session"/>
<jsp:useBean id="roomList" type="java.util.ArrayList<schoolManager.Room>" scope="request"/>
<jsp:useBean id="reviewList" type="java.util.ArrayList<schoolManager.Review>" scope="request"/>

<html>
  <head>
    <meta charset="UTF-8">
      <title>top</title>
      <link rel="stylesheet" type="text/css" href="/Seven_Wonders/css/TOP.css"></head>
      <script type="text/javascript" src="/Seven_Wonders/js/top.js"></script>
      <body>
        <div style="width: 700; margin: 0 auto;">

          <% if(message != null){ %>
            <font color="red"><%=message %></font>
            <br>
            <% } %>

            <div align=right>
              ようこそ、<%=userName %>さん
              <a href="?action=logout">（ログアウト）</a>
            </div>

            <div id="tab_box">
              <ul class="tab_all">

                <li>
                  <a href="#tab1" class="tab1" onClick="change_tab('tab1');return false;">rannking</a>
                </li>

                <li>
                  <a href="#tab2" class="tab2" onClick="change_tab('tab2');return false;">review</a>
                </li>

                <li>
                  <a href="#tab3" class="tab3" onClick="change_tab('tab3');return false;">map</a>
                </li>
              </ul>

              <div id="tab1" class="tab">
                <p>ランキング<br></p>
                  <table border=1>
                    <tr>

                      <td>
                        <div>content</div>
                      </td>
                      <td>time</td>
                      <td>build</td>
                      <td>star</td>

                    </tr>

                    <% for(int i =0; i< reviewList.size();i++){%>
                      <tr>
                        <td><%= reviewList.get(i).getText() %></td>
                        <td><%= reviewList.get(i).getTime() %></td>
                      <%
			String build = "";
			int id = reviewList.get(i).getPost_map_id();
			if (id == 0){
				build = "片柳研究棟";
			}

			else if (id == 1) {
				build = "FOODS FUU";
			}
			else if (id == 2) {
				build = "研究棟A";
			}
			else if (id == 3) {
				build = "本部棟";
			}
			else if (id == 4) {
				build = "図書館棟";
			}
			else if (id == 5) {
				build = "厚生棟";
			}
			else if (id == 6) {
				build = "メディアホール";
			}
			else if (id == 7) {
				build = "講義棟A";
			}
			else if (id == 8) {
				build = "講義実権棟";
			}
			else if (id == 9) {
				build = "研究棟C";
			}
			else if (id == 10) {
				build = "実権棟A";
			}
			else if (id == 11) {
				build = "体育館";
			}
			else if (id == 12) {
				build = "講義棟D";
			}
		   %>
                        <td><%=build%></td>
                        <td><%= reviewList.get(i).getStar() %></td>

                      </tr>
                    <%}%>
                  </table>
                </div>

                <div id="tab2" class="tab">
                  <p>レビュー<br></p>
                    <form action="?action=rev" method="post">
                      <div>
                        <label for="name">Name:</label>
                        <%=userName %>
                      </div>

                      <div>
                        <label for="room_name">Build:</label>
                        <select name="build">
                          <option value="0">片柳研究棟</option>
                          <option value="1">FOODS FUU</option>
                          <option value="2">研究棟A</option>
                          <option value="3">本部棟</option>
                          <option value="4">図書館棟</option>
                          <option value="5">厚生棟</option>
                          <option value="6">メディアホール</option>
                          <option value="7">講義棟A</option>
                          <option value="8">講義実験棟</option>
                          <option value="9">研究棟C</option>
                          <option value="10">実験棟A</option>
                          <option value="11">体育館</option>
                          <option value="12">講義棟D</option>
                        </select>
                      </div>

                      <div>
                        <label for="msg">Massage:</label>
                        <textarea type="msg" name="msg"></textarea>
                        <div class="hyouka">
                          <input id="hoshi1" type="radio" name="hoshi" value="5"/>
                          <label for="hoshi1">★</label>
                          <input id="hoshi2" type="radio" name="hoshi" value="4"/>
                          <label for="hoshi2">★</label>
                          <input id="hoshi3" type="radio" name="hoshi" value="3"/>
                          <label for="hoshi3">★</label>
                          <input id="hoshi4" type="radio" name="hoshi" value="2"/>
                          <label for="hoshi4">★</label>
                          <input id="hoshi5" type="radio" name="hoshi" value="1"/>
                          <label for="hoshi5">★</label>
                        </div>
                      </select>
                    </div>
                    <div class="button">
                      <button type="submit">Send your message</button>
                    </div>
                  </form>
                </div>

                <div id="tab3" class="tab">
                  <h1>build</h1>
                  <table border=1>
                    <tr>
                      <td>建物ID</td>
                      <td>建物名</td>
                      <td>フロア名</td>
                      <td>クリック回数</td>
                    </tr>

                    <% for(int i =0; i< roomList.size();i++){%>
                      <tr>
                        <td><%= roomList.get(i).getId() %></td>
                        <td><%= roomList.get(i).getBuild() %></td>
                        <td><%= roomList.get(i).getFloor() %></td>
                        <td><%= roomList.get(i).getCount() %></td>
                      </tr>
                    <%}%>
                  </table>
                </div>
              </div>
            </div>
          </body>
        </html>
