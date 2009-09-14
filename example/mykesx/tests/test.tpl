Gold & Hot Rod Red, as seen in the new <a href="http://blog.markturansky.com/archives/51">Iron Man trailer</a>!
<table cellspacing="0" cellpadding="4">
<% for(var i = 0; i < 10; i++){ %>
  <tr>
    <td style="background-color: <%= i % 2 == 0 ? 'red' : 'gold' %>">
        Hi, <%=name%>! i is <%= i %>
    </td>
  </tr>
<% } %>
</table>
