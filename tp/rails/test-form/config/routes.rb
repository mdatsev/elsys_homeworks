Rails.application.routes.draw do
	get '/', to: 'form#form'
	post '/', to: 'form#test'
end
