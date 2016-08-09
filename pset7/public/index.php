<?php

    // configuration
    require("../includes/config.php"); 
    
    // obtain user data
    $id = $_SESSION["id"];
    $user = query("SELECT * FROM `users` WHERE id = ?", $id)[0];
    
    // obtain portfolio data
    $records = query("SELECT * FROM `portfolio` WHERE id = ?", $id);
    
    // find most recent prices
    $portfolio = [];
    
    foreach($records as $record)
    {
        $stock = lookup($record["symbol"]);
        
        $portfolio[] = [
            
            "name" => $stock["name"],
            "symbol" => $record["symbol"],
            "price" => $stock["price"],
            "shares" => $record["shares"],
            "purchase_val" => $record["purchase_val"],
            "current_val" => $stock["price"] * $record["shares"],
            "gain" => $stock["price"] * $record["shares"] - $record["purchase_val"]
        ];
    }
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "user" => $user, "portfolio" => $portfolio]);

?>
