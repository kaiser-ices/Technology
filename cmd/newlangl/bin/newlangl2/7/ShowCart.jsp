<%@ page contentType="text/html;charset=UTF-8"%>
<jsp:useBean id="message" class="java.lang.String" scope="request"/>
<jsp:useBean id="userName" class="java.lang.String" scope="session"/>
<jsp:useBean id="cart" class="webshop.Cart" scope="session"/>

<html>
  <head>
    <title><%=ueerName %>のカート内一覧</title>
  </head>
</body>
<di style="width: 500; margin: 0 auto;">

  <% if(message !=null){ %>
  <font color="red"><%= message %></font>
  <br>
    <% } %>

    <div align=right>
      ようこそ、<%=userName %>さん
      <a href="?action=logout">（ログアウト）</a>
    </div>

    <h1><%= userName %>さんのカート</h1>
    <hr>

      <table border=1>
        <tr>
          <td>表品ID</td>
          <td>商品名</td>
          <td>価格</td>
          <td>削除</td>
        </tr>
        <% for(int i=0; i<cart.getSize();i++){ %>
        <tr>
          <td><%=cart.getItem(i).getID()%></td>
          <td><%=cart.getItem(i).getName()%></td>
          <td><%=cart.getItem(i).getPrice()%></td>
          <td><a href="?action=del&index=<%= i %>">カートから削除</a></td>
        </tr>
        <% } %>
        <tr>
          <td colospan=4 aligin=right>合計:<%= cart.getSumPrice() %>円</td>
        </tr>
      </table>
      <a href="?action=showItems">商品一覧へ</a>

    </div>
  </body>
</html>
