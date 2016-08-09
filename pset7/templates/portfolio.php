<table class="table table-striped">
    <tr>
        <th>Name</th>
        <th>Symbol</th>
        <th>Price</th>
        <th>Shares</th>
        <th>Purchase Value</th>
        <th>Current Value</th>
        <th>Gain</th>
    </tr>
    
    <?php
    
    foreach($portfolio as $entry)
    {
        echo("<tr>");
        
        foreach($entry as $value)
        {
            echo("<td>" . $value . "</td>");
        }
        echo("</tr>");
    }
    
    ?>
    
    <tr>
        <th>CASH</th>
        <th colspan = 4></th>
        <th><?= $user["cash"]?></th>
        <th></th>
    </tr>
</table>

<div>
    <a href="logout.php">Log Out</a>
</div>
