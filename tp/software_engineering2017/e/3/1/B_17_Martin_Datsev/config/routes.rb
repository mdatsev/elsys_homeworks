Rails.application.routes.draw do
  get '/B_17_Martin_Datsevschools', to: 'students#index'
  resources :schools
  resources :students
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
