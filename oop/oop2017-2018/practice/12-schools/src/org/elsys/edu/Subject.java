package org.elsys.edu;

public class Subject {

	private String name;
	private boolean mandatory;
	
	public Subject(String name, boolean mandatory) {
		setName(name);
		setMandatory(mandatory);
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public boolean isMandatory() {
		return mandatory;
	}

	public void setMandatory(boolean mandatory) {
		this.mandatory = mandatory;
	}
	
	@Override
	public boolean equals(Object obj)
	{
	    if (obj == null) {
	        return false;
	    }
	    if (!Subject.class.isAssignableFrom(obj.getClass())) {
	        return false;
	    }
	    final Subject other = (Subject) obj;
	    if ((this.name == null) ? (other.name != null) : !this.name.equals(other.name)) {
	        return false;
	    }
	    if (this.mandatory != other.mandatory) {
	        return false;
	    }
	    return true;
	}
	
	@Override
	public int hashCode()
	{
		return name.hashCode() + (mandatory ? 0 : 1);
	}
	
}
