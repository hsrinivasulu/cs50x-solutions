<?php

    // configuration
    require("../includes/config.php"); 
    $id = $_SESSION["id"];
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // retrieve list of stocks
        $records = array_filter(query("SELECT * FROM `portfolio` WHERE `id` = ?", $id));
        
        if (empty($records))
            apologize("You do not have any stocks to sell.");
        else
            render("sell_form.php", ["title" => "Sell", "records" => $records]);
        
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = $_POST["symbol"];
        if (empty($symbol))
            redirect("sell.php");
        else
        {
            $price = lookup($symbol)["price"];
            $record = query("SELECT * FROM `portfolio` WHERE `id` = ? AND `symbol` = ?", $id, $symbol)[0];
            $shares = $record["shares"];
            
            // email
            $email_id = query("SELECT email from `users` where id = ?", $id)[0]["email"];
            $status = email($email_id, $symbol . " sold on C$50 Finance", $shares . " shares of " . $symbol . " at $" . $price . " per share were sold for a total of $".$price * $shares );
            
            // transaction
            query("INSERT INTO `transactions`(`id`, `type`, `symbol`, `shares`, `price`) VALUES (?, \"SELL\", ?, ?, ?)", $id, $symbol, $shares, $price );
            
            query("DELETE FROM `portfolio` WHERE `id` = ? AND `symbol` = ?", $id, $symbol);
            query("UPDATE `users` SET cash = cash + ? where id = ?", $price * $shares, $id);
            
            render("sell_display.php", ["title" => "Sell", "price" => $price, "shares" => $shares, "symbol" => $symbol, "status" => $status]);
        }
    }
?>

