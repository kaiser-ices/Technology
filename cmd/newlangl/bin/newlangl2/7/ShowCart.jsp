<%@ page contentType="text/html;charset=UTF-8"%>
<jsp:useBean id="message" class="java.lang.String" scope="request"/>
<jsp:useBean id="userName" class="java.lang.String" scope="session"/>
<jsp:useBean id="cart" class="webshop.Cart" scope="session"/>

<html>
  <head>
    <title><%=ueerName %>�̃J�[�g���ꗗ</title>
  </head>
</body>
<di style="width: 500; margin: 0 auto;">

  <% if(message !=null){ %>
  <font color="red"><%= message %></font>
  <br>
    <% } %>

    <div align=right>
      �悤�����A<%=userName %>����
      <a href="?action=logout">�i���O�A�E�g�j</a>
    </div>

    <h1><%= userName %>����̃J�[�g</h1>
    <hr>

      <table border=1>
        <tr>
          <td>�\�iID</td>
          <td>���i��</td>
          <td>���i</td>
          <td>�폜</td>
        </tr>
        <% for(int i=0; i<cart.getSize();i++){ %>
        <tr>
          <td><%=cart.getItem(i).getID()%></td>
          <td><%=cart.getItem(i).getName()%></td>
          <td><%=cart.getItem(i).getPrice()%></td>
          <td><a href="?action=del&index=<%= i %>">�J�[�g����폜</a></td>
        </tr>
        <% } %>
        <tr>
          <td colospan=4 aligin=right>���v:<%= cart.getSumPrice() %>�~</td>
        </tr>
      </table>
      <a href="?action=showItems">���i�ꗗ��</a>

    </div>
  </body>
</html>
