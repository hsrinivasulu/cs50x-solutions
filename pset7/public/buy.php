<?php

    // configuration
    require("../includes/config.php"); 
    $id = $_SESSION["id"];
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
     else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $symbol = strtoupper(filter($_POST["symbol"]));
        $shares = filter($_POST["shares"]);
        
        if (empty($symbol))
            apologize("Please enter a stock symbol");
        if (!preg_match("/^\d+$/", $shares) || $shares == 0)
            apologize("Please enter a positive, integral number of shares");
        
        $quote = lookup($symbol);
        
        if ($quote == FALSE)
            apologize("Unable to find " . $symbol);
        
        $price = $quote["price"];
        $cash = query("SELECT `cash` FROM `users` WHERE id = ?", $id)[0]["cash"];
        
        if ($price * $shares > $cash)
            apologize("Insufficient funds" . ($cash >= $price)?(". You may only purchase " . floor($cash/$price) . " shares."):".");
            
        // done error checking
        
        $check = array_filter(query("SELECT * FROM `portfolio` WHERE id = ? AND symbol = ?", $id, $symbol));
        
        // email
        $email_id = query("SELECT email from `users` where id = ?", $id)[0]["email"];
        $status = email($email_id, $symbol . " bought on C$50 Finance", $shares . " shares of " . $symbol . " at $" . $price . " per share were bought for a total of $".$price * $shares );
        
        // transactions
        query("INSERT INTO `transactions` (`id`, `type`, `symbol`, `shares`, `price`) VALUES (?, \"BUY\", ?, ?, ?)", $id, $symbol, $shares, $price );

        if(empty($check))
            query("INSERT INTO `portfolio` (id, symbol, shares, purchase_val) VALUES(?,?,?,?)", $id, $symbol, $shares, $price * $shares);
        else
            query("UPDATE `portfolio` SET shares = shares + ?, purchase_val = purchase_val + ? WHERE id = ? AND symbol = ?", $shares, $price * $shares, $id, $symbol);
            
        query("UPDATE `users` SET cash = cash - ? WHERE id = ?", $price * $shares, $id);
        
        
        render("buy_display.php", ["title" => "Buy", "price" => $price, "shares" => $shares, "symbol" => $symbol, "status" => $status]);
    }
?>
