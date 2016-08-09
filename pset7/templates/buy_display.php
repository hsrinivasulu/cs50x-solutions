Bought <?= $shares ?> shares of <?= $symbol ?> at $<?= $price ?> each for a grand total of $<?= $shares * $price ?>.<br/>

<?php
    if($status)
        echo("A receipt has been sent to your email address.");
    else
        echo("However, we were unable to send your receipt to your email address.");
?>
