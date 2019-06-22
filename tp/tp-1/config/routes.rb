Rails.application.routes.draw do
  resources :text_files
  match '/sums', :to => 'sums#form', :via => [:get]
  match '/filters', :to => 'filters#form', :via => [:get]
  match '/sums', :to => 'sums#calc', :via => [:post]
  match '/filters', :to => 'filters#calc', :via => [:post]
  match '/intervals', :to => 'intervals#calc', :via => [:post]
  match '/lin_regressions', :to => 'lin_regressions#calc', :via => [:post]
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
