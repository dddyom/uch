<?php 

$first_variable = $_POST["first_variable"];
$second_variable = $_POST["second_variable"];

switch ($_POST["operation"]){
	case 'plus':
	echo $first_variable+ $second_variable;
	break;
	case 'minus':
	echo $first_variable- $second_variable;
	break;
	case 'multi':
	echo $first_variable* $second_variable;
	break;
	case 'div':
	echo $first_variable/ $second_variable;
	break;
	case 'pow':
	echo pow($first_variable, $second_variable);
	break;
	case 'sqrt':
	echo pow($second_variable, 1/$first_variable);
	break;
	case 'sin':
	echo sin($first_variable);
	break;	
	case 'cos':
	echo cos($first_variable);
	break;
	case 'tg':
	echo tan($first_variable);
	break;
	case 'ctg':
	echo 1/tan($first_variable);
	break;							
	default:

	break;
}
?>


