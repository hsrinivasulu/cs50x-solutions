<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select name="symbol" class="dropdown">
                <?php
                 
                    foreach($records as $record)
                    {
                        $symbol = $record["symbol"];
                        echo("<option value =\"" . $symbol . "\">" . $symbol . "</option>\n");
                    }  
                ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
