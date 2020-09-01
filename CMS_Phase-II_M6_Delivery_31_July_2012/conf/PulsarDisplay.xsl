<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="html" />
	<xsl:template match="/groups">		
		<xsl:apply-templates />
	</xsl:template>	
	
	<xsl:template match="group">
	
	<xsl:variable name="frmName">		
		<xsl:value-of select="@formName" />
	</xsl:variable>	
	
		<div class="ifoscBox2Table">
			<div id="spectrallinedisplay" class="subHeaderTitle">
			<xsl:value-of select="@name" />			
			<xsl:apply-templates />
			</div>
		</div>

	</xsl:template>
	<xsl:template match="controls">
		<table width="100%" border="0" cellspacing="0" cellpadding="0"
			bgcolor="#FFFFFF" class="bgrndBl">
			
					<xsl:apply-templates/>
		</table>
	</xsl:template>
	<xsl:template match="row">
	<tr>
				<xsl:if test="@oddrow='yes'">
						<xsl:attribute name="class">oddRow</xsl:attribute>				
				</xsl:if>
		<xsl:apply-templates select="column/control" />
	</tr>			
	</xsl:template>
	

<xsl:template match="control">	
	<xsl:variable name="label" select="./label"/>
	<xsl:variable name="class" select="./class"/>
			
		<xsl:variable name="type" select="./type"/>
		<xsl:variable name="colspan" select="./colspan"/>		
		<xsl:choose> 
			<xsl:when test="$type='Text'">
				<td colspan="{$colspan}">
					<xsl:element name="input">
						<xsl:attribute name="type">Text</xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>
						<xsl:attribute name="maxlength"><xsl:value-of select="maxlength"/></xsl:attribute>						
						<xsl:attribute name="style"><xsl:value-of select="style"/></xsl:attribute>	
						<xsl:attribute name="class"><xsl:value-of select="@class" /></xsl:attribute>
						<xsl:attribute name="metaData"><xsl:value-of select="metaData"/></xsl:attribute>	
						<xsl:if test="@disabled='true'">
							<xsl:attribute name="readonly"><xsl:value-of select="readonly"/></xsl:attribute>	
						</xsl:if>							
					</xsl:element>
				</td>
			</xsl:when>
			
			<xsl:when test="$type='DropDown'">
				<xsl:variable name="fieldName">
					<xsl:value-of select="name"/>
				</xsl:variable>		
				<td colspan="{$colspan}" class="{$class}">
					<xsl:element name="select">
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>						
						<xsl:attribute name="onchange"><xsl:value-of select="onchange"/>(this)</xsl:attribute>
						<option value="Select">Select</option>
						<xsl:apply-templates select="options/option" />
					</xsl:element>
				</td>
			</xsl:when>	

		<xsl:when test="$type='MultipleSelectList'">
				<xsl:variable name="fieldName">
					<xsl:value-of select="name"/>
				</xsl:variable>		
				<td colspan="{$colspan}" class="{$class}">
					<xsl:element name="select">
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>
						<xsl:attribute name="multiple">multiple</xsl:attribute>
						<xsl:attribute name="size"><xsl:value-of select="size"/></xsl:attribute>
						<xsl:attribute name="style"><xsl:value-of select="style"/></xsl:attribute>
						<xsl:attribute name="onchange"><xsl:value-of select="onchange"/>(this)</xsl:attribute>						
						<xsl:apply-templates select="optgroup" />
					</xsl:element>
				</td>
			</xsl:when>	
			
			<xsl:when test="$type='radio'">
				<td colspan="{$colspan}">
					<xsl:element name="input">
						<xsl:attribute name="type">radio</xsl:attribute>
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>
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
				</td>
			</xsl:when>	
			
			<xsl:when test="$type='checkbox'">				
				<xsl:variable name="ssName">
					<xsl:value-of select="subSystemName"/>
				</xsl:variable>					
				<td>
					<xsl:element name="input">
						<xsl:attribute name="type">checkbox</xsl:attribute>
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>													
						<xsl:attribute name="class">disabledControl</xsl:attribute>				
					</xsl:element>
					<input type="hidden" name="{name}" value="false" />
				</td>
			</xsl:when>			
			
			<xsl:when test="$type='Button'">
				<td colspan="{$colspan}">
					<xsl:element name="input">
						<xsl:attribute name="type">Submit</xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
						<xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>
						<xsl:attribute name="onclick"><xsl:value-of select="./onclick"/>(this)</xsl:attribute>
						<xsl:attribute name="class">buttonNormal</xsl:attribute>				
					</xsl:element>					
				</td>
			</xsl:when>	
			<xsl:when test="$type='LABEL'">
				<td colspan="{$colspan}">
					<xsl:element name="label">
						<xsl:value-of select="./label"/>
						<xsl:attribute name="id"><xsl:value-of select="cmdid"/></xsl:attribute>							
					</xsl:element>
				</td>
			</xsl:when>
		</xsl:choose>
</xsl:template>
		
		
<xsl:template match="option">
	<xsl:variable name="select" select="./selected"/>
	<xsl:element name="option">
		<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
		<xsl:if test="$select='true'"><xsl:attribute name="selected">true</xsl:attribute></xsl:if>
		<xsl:value-of select="key"/>
	</xsl:element>
</xsl:template>

<xsl:template match="optgroup">	
	<xsl:element name="optgroup">
		<xsl:attribute name="label"><xsl:value-of select="label"/></xsl:attribute>
		<xsl:apply-templates select="option" />
	</xsl:element>
</xsl:template>



</xsl:stylesheet>