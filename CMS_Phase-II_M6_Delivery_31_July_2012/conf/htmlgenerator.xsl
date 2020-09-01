<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">
<xsl:output method="html" />
<xsl:template match="/groups">
<script type="text/javascript">

<![CDATA[

function handleBackendCommands(cmdName){
	
	document.getElementById('cmdSelector').value = "backend";
	document.getElementById('cmdForExecution').value = cmdName;
	applyCommand('true');
}

]]>

</script>
	<xsl:apply-templates/>
</xsl:template>
<xsl:template match="group">
	<div class=" box2Table">
		<div id="legends" class="HeaderTitle"><xsl:value-of select="@name"/>
			<xsl:apply-templates/>
		</div>
	</div>
</xsl:template>

<xsl:template match="controls">
	   <table width="95%" border="0" cellspacing="0" cellpadding="0" bgcolor="#FFFFFF">
	    
			<xsl:choose>
				<xsl:when test="@type='channelheader'">
					<tr style="background-color:red">	
						<th width="27%"></th>
						<th width="21%">POL1</th>
						<th width="30%"></th>
						<th></th>
						<th width="22%">POL2</th>
						<th></th>
					</tr>
					<tr>
						<td width="27%"></td>
						<td width="21%"></td>
						<td width="15%"></td>
						<td width="22%"></td>					
					</tr>
				</xsl:when>
				<xsl:otherwise>
					<tr>
						<td width="27%"><strong></strong></td>
						<td width="21%"><strong></strong></td>
						<td width="15%"><strong></strong></td>
						<td width="22%"><strong></strong></td>				
					</tr>	
				</xsl:otherwise>
			</xsl:choose>		
		<xsl:apply-templates/>
	   </table>
</xsl:template>

<xsl:template match="row">
	<tr>
		<xsl:apply-templates select="column/control" />
	</tr>			
</xsl:template>
<xsl:template match="control">
	<xsl:choose>
		<xsl:when test="@colspan!=''">
			<td colspan="{@colspan}"><strong><xsl:value-of select="label"/></strong></td>
		</xsl:when>
		<xsl:otherwise>
			<td><strong><xsl:value-of select="label"/></strong></td>
		</xsl:otherwise>
	</xsl:choose>
	<xsl:variable name="type" select="./type"/>
	<xsl:variable name="subSystemName" select="./subSystemName"/>
      <xsl:choose>
		<xsl:when test="$type='Button'">
			<td>
			<iframe name="i{name}" id="i{name}" height="0" width="0"
			frameborder="0" scrolling="no"></iframe>
				
					<xsl:element name="input">
						<xsl:attribute name="type">Button</xsl:attribute>
						<xsl:attribute name="name"><xsl:value-of select="name"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="onclick">handleBackendCommands('<xsl:value-of select="./name"/>');</xsl:attribute>
						<xsl:choose>
							<xsl:when test="@disabled='true'">
								<xsl:attribute name="disabled">true</xsl:attribute>
								<xsl:attribute name="class">disabledControl width60 buttonNormalDis</xsl:attribute>				
							</xsl:when>
							<xsl:otherwise>
								<xsl:attribute name="class">width60 buttonNormal</xsl:attribute>
							</xsl:otherwise>
						</xsl:choose>	
					</xsl:element>
					<input type="hidden" name="{name}__{subSystemName}" value="" />
			</td>
		</xsl:when>	  
		<xsl:when test="$type='Text'">
			<td>
			<xsl:element name="input">
				<xsl:attribute name="type">Text</xsl:attribute>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
				<xsl:attribute name="name"><xsl:value-of select="name"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="id"><xsl:value-of select="cmdid"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:if test="@disabled='true'">
					<xsl:attribute name="disabled">true</xsl:attribute>
					<xsl:attribute name="class">disabledControl width60</xsl:attribute>				
				</xsl:if>
			</xsl:element>
			</td><td>
			<xsl:value-of select="unit"/>
			</td>
		</xsl:when>
		<xsl:when test="$type='DropDown'">
			<td>
			<xsl:element name="select">
				<xsl:attribute name="name"><xsl:value-of select="name"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="id"><xsl:value-of select="cmdid"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:if test="@disabled='true'">
					<xsl:attribute name="disabled">true</xsl:attribute>
					<xsl:attribute name="class">disabledControl</xsl:attribute>				
				</xsl:if>				
				<xsl:apply-templates select="options/option" />
			</xsl:element>
			</td><td>
			<xsl:value-of select="unit"/>
			</td>
		</xsl:when>
		<xsl:when test="$type='checkbox'">
			<td>
			<xsl:element name="input">
				<xsl:attribute name="type">checkbox</xsl:attribute>
				<xsl:attribute name="name"><xsl:value-of select="name"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="id"><xsl:value-of select="cmdid"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
				<xsl:variable name="selected" select="./checked"/>
				<xsl:if test="$selected='true'">
					<xsl:attribute name="checked">true</xsl:attribute>	
				</xsl:if>
				
				<xsl:if test="@disabled='true'">
					<xsl:attribute name="disabled">true</xsl:attribute>
					<xsl:attribute name="class">disabledControl</xsl:attribute>				
				</xsl:if>				
			</xsl:element>
			<input type="hidden" name="{name}__{subSystemName}" value="false" />
			</td><td><xsl:value-of select="unit"/>
			</td>
		</xsl:when>
		<xsl:when test="$type='radio'">
			<td>
			<xsl:element name="input">
				<xsl:attribute name="type">radio</xsl:attribute>
				<xsl:attribute name="name"><xsl:value-of select="name"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="id"><xsl:value-of select="cmdid"/>__<xsl:value-of select="$subSystemName"/></xsl:attribute>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
				
				<xsl:variable name="selected" select="./checked"/>
				<xsl:if test="$selected='true'">
					<xsl:attribute name="checked">true</xsl:attribute>	
				</xsl:if>
				<xsl:if test="@disabled='true'">
					<xsl:attribute name="disabled">true</xsl:attribute>
					<xsl:attribute name="class">disabledControl</xsl:attribute>				
				</xsl:if>				
			</xsl:element>
			</td><td><xsl:value-of select="unit"/>
			</td>
		</xsl:when>		
	</xsl:choose>
</xsl:template>
<xsl:template match="option">
	<xsl:variable name="select" select="./selected"/>
	<xsl:element name="option">
		<xsl:attribute name="value"><xsl:value-of select="key"/></xsl:attribute>
		<xsl:if test="$select='true'"><xsl:attribute name="selected">true</xsl:attribute></xsl:if>
		<xsl:value-of select="key" />
	</xsl:element>
</xsl:template>
</xsl:stylesheet>