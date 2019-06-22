Rails.application.routes.draw do
	# get 'welcome/index'
	root 'welcome#index'
	post '/upload', to: 'welcome#upload'
	# For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
