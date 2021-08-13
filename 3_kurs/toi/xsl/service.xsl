<xsl:stylesheet version = "1.0" 
xmlns:xsl = "http://www.w3.org/1999/XSL/Transform"> 


<xsl:template match = "/service">

	<html>
	   <head><title><xsl:value-of select="about/title" /></title></head>

		<body>
			<h2>Order List</h2>
		
			<table border="1">
				<tr bgcolor="green">
					<th>Client</th>
					<th>Phone Model</th>
					<th>Breaking</th>
					<th>Phone number</th>
					<th>Price</th>
					<th>Worker</th>
				</tr>
				<xsl:for-each select = "orders/order">
				
					<tr>
						<td><xsl:value-of select = "client"/></td>
						<td><xsl:value-of select = "model"/></td>
						<td><xsl:value-of select = "breaking"/></td>
						<td><xsl:value-of select = "telephone"/></td>
						<td><xsl:value-of select = "price"/></td>
						<td><xsl:value-of select = "worker"/></td>
					</tr>
				
				</xsl:for-each>
				
			</table>
			
			
			<h2>Client List</h2>
			
			<table border = "1">
				<tr bgcolor="yellow">
					<th>Name</th>
					<th>Phone Model</th>
					<th>Mail</th>
					<th>Phone number</th>
					<th>Address</th>
				</tr>
				
				<xsl:for-each select = "clients/client">
				
					<tr>
						<td><xsl:value-of select = "name"/></td>
						<td><xsl:value-of select = "model"/></td>
						<td><xsl:value-of select = "mail"/></td>
						<td><xsl:value-of select = "telephone"/></td>
						<td><xsl:value-of select = "address"/></td>
					</tr>
				
				</xsl:for-each>
				
			</table>
			
			<h2>Client List</h2>
			
			<table border = "1">
				<tr bgcolor="blue">
					<th>Name</th>
					<th>Salary</th>
					<th>Mail</th>
					<th>Phone number</th>
					<th>Address</th>
				</tr>
				
				<xsl:for-each select = "employees/employee">
				
					<tr>
						<td><xsl:value-of select = "name"/></td>
						<td><xsl:value-of select = "salary"/></td>
						<td><xsl:value-of select = "mail"/></td>
						<td><xsl:value-of select = "telephone"/></td>
						<td><xsl:value-of select = "address"/></td>
					</tr>
				
				</xsl:for-each>
				
			</table>
			
			<h2><xsl:value-of select="about/title" /></h2>
			<p><xsl:value-of select="about/description" /></p>
		</body>
	</html>
</xsl:template>
</xsl:stylesheet>
