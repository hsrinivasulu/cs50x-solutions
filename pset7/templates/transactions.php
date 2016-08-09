<table class="table table-striped">
    <tr>
        <th>Serial Number</th>
        <th>Type</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
        <th>Timestamp</th>
    </tr>
    
    <?php
    
    $count = 1;
    
    foreach($records as $record)
    {
        echo("<tr>");
        echo("<td>" . $count . "</td>");
        echo("<td>" . $record["type"] . "</td>");
        echo("<td>" . $record["symbol"] . "</td>");
        echo("<td>" . $record["shares"] . "</td>");
        echo("<td>" . $record["price"] . "</td>");
        echo("<td>" . $record["timestamp"] . "</td>");
        echo("</tr>");
        
        $count++;
    }
    
    ?>
    
</table>
